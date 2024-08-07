/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:44:04 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/07/18 13:33:33 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    catch_error(int i, char *command)
{

    if (i == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(command, 2);
		ft_putchar_fd('\n', 2);
		exit(errno);
	}
}

void    close_fds_child(int   fdin, int fdout, t_exec *tree)
{
    if (fdin == tree->fdin && fdout == tree->fdout)
        return;
    if (fdin != tree->fdin)
        catch_error(close(fdin), "close");
    else if (fdout != tree->fdout)
        catch_error(close(fdout), "close");
}

void    open_files(t_exec *tree, t_minishell *mini)
{
    int fdin;
    int fdout;

    fdin = tree->fdin;
    fdout = tree->fdout;
    while (tree->iofiles)
    {
        if (tree->iofiles->type == APPEND)
        {
            if (tree->iofiles->ambiguous)
            {
                printf("Ambigius file %s\n",ft_split_local(tree->iofiles->token,' ', mini)[1]);
                exit(1);
            }
            close_fds_child(tree->fdin, fdout, tree);
            fdout = open(ft_split_local(tree->iofiles->token,' ',mini)[1], O_CREAT | O_RDWR | O_APPEND, 0644);
        }
        else if (tree->iofiles->type == OUT_RED)
        {
            close_fds_child(tree->fdin, fdout, tree);
            if (tree->iofiles->ambiguous)
            {
                printf("Ambigius file %s\n",ft_split_local(tree->iofiles->token,' ',mini)[1]);
                exit(1);
            }
            fdout = open(ft_split_local(tree->iofiles->token,' ',mini)[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
        }
         else if (tree->iofiles->type == IN_RED)
        {
            if (tree->iofiles->ambiguous)
            {
                printf("Ambigius file %s\n",ft_split_local(tree->iofiles->token,' ',mini)[1]);
                exit(1);
            }
            close_fds_child(fdin, tree->fdout, tree);
            fdin = open(ft_split_local(tree->iofiles->token,' ',mini)[1], O_RDWR);
        }
        else if (tree->iofiles->type == DEL)
        {
            close_fds_child(fdin, tree->fdout, tree);
            fdin = tree->fdin;
        }
        tree->iofiles = tree->iofiles->next;
    }
    tree->fdin = fdin;
    tree->fdout = fdout;
    
}

char    *get_path(t_minishell *mini, t_tokenizer *tokens)
{
    int     i;
    char    *test;

    i = 0;
    while (mini->paths[i])
    {
        test = ft_strjoin(mini->paths[i], tokens->token, mini, &mini->global);
        if (access(test , F_OK) == 0)
            return (test);
        i++;
    }
    return (NULL);
}


int    run_command(t_exec *tree, t_minishell *mini)
{
    char    *path;
    pid_t   pid;
    // int     status;
    int     st;

    st = 0;
    if (!mini)
        return (0);
    pid = fork();
    if (pid == 0 && mini && tree)
    {
        open_files(tree, mini);
        dup2(tree->fdin, 0);
        dup2(tree->fdout, 1);
        if (tree->fdin != 0)
            close(tree->fdin);
        if (tree->fdout != 1)
            close(tree->fdout);
        path = get_path(mini, tree->tokens);
        if (!path)
            catch_error(-1, tree->tokens->token);
        catch_error (execve(path, &tree->tokens->token, mini->env),tree->tokens->token);
        exit(0);
    }
    else 
        waitpid(pid, NULL, 0);
    return (st);
}

int    execute_all(t_exec *tree, t_minishell *mini)
{

    if (!tree || !tree->tokens)
        return (0);

    // printf("%d\n", tree->type); 
    if (tree->type == CMD)
    {
        prepare_node_for_execute(mini, tree);
        return run_command(tree, mini);
    }
    // else if (tree->type == OR)
    //     (!execute_all(tree->left, mini) || execute_all(tree->right, mini));
    // else if (tree->type == AND)
    //     (execute_all(tree->left,  mini) && !execute_all(tree->right,  mini));
    // printf("%s , %s\n",tree->left->tokens->token, tree->right->tokens->token);
    execute_all(tree->left, mini);
    execute_all(tree->right, mini);
    return (0);
}