#ifndef USERINPUT_H_
#define USERINPUT_H_

char* getUserInput()
{
	printf(" > ");
	size_t bufferSize = 100;
	char* buffer = calloc(bufferSize, sizeof(char));
	if(buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	getline(&buffer, &bufferSize, stdin);
	return buffer;
}

#endif /* USERINPUT_H_ */
