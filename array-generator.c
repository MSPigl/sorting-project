/*
 * Function to generate input arrays
 */
void* makeArray(int numElement, int elementType)
{
   return malloc(numElement * elementType);
}
