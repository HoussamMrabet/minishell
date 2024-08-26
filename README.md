# MINISHELL

## Errors to handle:
### - possible segv in lexer
### - echo 42   42    '  '42 // ADDITIONAL SPACES

### - export x="first second"
### - export w="one tow"

### - export $w=$x=$x=$x

### - cat &

### - cd $PWD hi

### - exit -100

### - echo < infile
###   echo < infiel | echo 42

### - echo 42 > /DIR/outfile | echo 1337

### - /includes == No such file or directory

### - ./miss
###   echo $?
###   1