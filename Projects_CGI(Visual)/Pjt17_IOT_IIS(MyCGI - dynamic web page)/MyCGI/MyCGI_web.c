#include <stdio.h>
#include "MyCGI_web.h"

void MyCGI_web(char* data)
{
	char* sp, * ep;
	printf("Content-Type: text/html; charset=euc-kr\n\n");
	printf("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\">\n");
	printf("<html>\n");
	printf("	<head>\n");
	printf("	<title> MyCGI.exe(Dynamic Web Page) </title>\n");
	printf("	</head>\n");
	printf("	<body>\n");
	printf("		<H2> Iot Testing(MyCGI - dynamic web page</H2>\n");
	printf("		<HR>\n");
	for (sp = ep = data; *ep; ep++) {
		if (*ep == '\n') {
				*ep = '\0';
				printf("%s\n<BR>", sp);
				sp = ep + 1;
			}
	}
	printf_s("%s\n<BR>\n", sp);
	printf("	</body>\n");
	printf("</html>\n");
}
