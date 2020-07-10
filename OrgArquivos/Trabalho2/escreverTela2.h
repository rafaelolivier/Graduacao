/*
* Abaixo seguem funções que fazem a escrita do binário em "stdout" (tela) pra poder ser comparado no run.codes.
*
* Funciona assim: você faz tudo o que tiver que fazer na funcionalidade no arquivo em disco, assim como ensinado nas aulas da disciplina.
* Ao fim da funcionalidade, você escolhe uma das funções abaixo (a que achar mais fácil de usar de acordo com sua implementação) e a função já cuida de tudo para você. É só chamar a função.
*
* "Qual função escolher?"
* As duas fazem A MESMA coisa: escrever na tela o arquivo binário para funcionar com o sistema do run.codes.
*     - Você escolhe a binarioNaTela1 se você ainda não fez o fclose no arquivo binário. Você passa o ponteiro 'FILE *' para ela e ela vai ler tudo e escrever na tela.
*     - Você escolhe a binarioNaTela2 se você já fez o fclose no arquivo binário. Você passa o nome do arquivo binário ("arquivoTrabX.bin") pra ela e ela vai ler tudo e escrever na tela.
*
* Você pode colocar isso num módulo .h separado, ou incluir as funções no próprio código .c: como preferir.
* VOCÊ NÃO PRECISA ENTENDER ESSAS FUNÇÕES. É só usar elas da forma certa depois de acabar a funcionalidade.
*
* Tá tudo testado e funcionando, mas qualquer dúvida acerca dessas funções, falar com o monitor Matheus (mcarvalhor@usp.br).
*/

	#include "otherfunctions.h"

	// Se você for incluir no .h separado, tá abaixo:

	#ifndef H_ESCREVERNATELA_
	#define H_ESCREVERNATELA_

	void binarioNaTela1(FILE *ponteiroArquivoBinario);
	void binarioNaTela2(char *nomeArquivoBinario);
	void trim(char *str);
	void scan_quote_string(char *str);

	#endif
