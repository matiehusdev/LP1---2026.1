# criando um arquivo de texto
arquivo = open('pyBasico.txt', 'w')
arquivo.write('Curso Python \n')
arquivo.write('Aula Prática \n')
arquivo.close()

# lendo o arquivo de texto
leitura = open('pyBasico.txt', 'r')
print(leitura.read())
leitura.close()

# continuar escrevendo no arquivo
escrever = open('pyBasico.txt', 'a')
escrever.write('Testando [a] para continuar escrevendo \n')
escrever.close()

escrever = open('pyBasico.txt', 'a')
escrever.write('Testando novamente [a] \n')
escrever.close()