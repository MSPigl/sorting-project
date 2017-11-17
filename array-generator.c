/*
 * Function to generate input arrays
 */
void* makeArray(int numElement, int elementType)
{
   return malloc(numElement * elementType);
}

int main()
{
   int* intArray = (int *)makeArray(10, sizeof(int));
   float* floatArray = (float *)makeArray(10, sizeof(float));
   char* charArray = (char *)makeArray(10, sizeof(char));
}
