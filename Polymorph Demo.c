void dog(int dog1){
	writeDebugStreamLine("Int");
}

void dog(float dog2){
	writeDebugStreamLine("Float");
}

task main()
{
	dog(5.45);
}
