# siC: Uma linguagem baseada em C incluindo fila como tipo primitivo

Este trabalho visa projetar e construir um analisador semântico para uma nova linguagem chamada siC - Structure in C, baseada na linguagem C. O siC acrescenta a estrutura de dados fila como tipo de dado primitivo e, para manipulá-la, adiciona certas operações próprias para tal (ver [PDF](https://github.com/gabepk/siC-AnalisadorSemantico/blob/master/siC.pdf)).

## Execução

$ make 

$ ./sic-compiler < teste.sic

## Output

* Erros léxicos
* Erros sintáticos
* Erros semânticos
* Árvore sintática 
* Tabela de símbolos
* Matriz de escopo
