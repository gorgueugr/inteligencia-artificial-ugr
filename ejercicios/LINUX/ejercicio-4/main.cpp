#include "GUI.h"
#include <pthread.h>
void junk() {
  int i;
  i=pthread_getconcurrency();
};

int main(int argc, char *argv[]){
	return GUI::startDraw(argc,argv);
}
 
