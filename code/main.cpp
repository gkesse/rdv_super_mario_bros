#include "rdv_application.h"

int main(int _argc, char** _argv)
{
	rdv_application app(_argc, _argv);
	app.run();
	return 0;
}
