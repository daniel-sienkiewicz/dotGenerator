void funkcja1();
void funkcja2();
void funkcja3();
void funkcja4();
void funkcja5();
void funkcja6();
void funkcja7();


void funkcja7(void){
	funkcja4();
}

void funkcja6(void){
	funkcja1();
}

void funkcja5(void){
}

void funkcja4(void){
	funkcja2();
}

void funkcja3(void){
	funkcja4();
	funkcja5();
	funkcja6();
}

void funkcja2(void){
}

void funkcja1(){
	funkcja7();
	funkcja2();
	funkcja3();
}
