#include <stdlib.h>
#include "TC1047_COM3_web.h"
#include "CGI_get_data.h"

int main(void) {
	char* data;

	data = (char*)malloc((DFL_N_HEAD + DFL_N_TAIL) * CHR_P_LINE);

	CGI_get_data("COM5", "tc1047", DFL_N_HEAD, DFL_N_TAIL, data);
	TC1047_COM3_web(data);

	free(data);
}