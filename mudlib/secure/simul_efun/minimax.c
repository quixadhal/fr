
// by Dank Mar 11 93.  max may be a reserved word, so maxi is safer
int maxi(int *array) {
  int i, j;
  if (!sizeof(array)) {
    notify_fail("Array must contain one or more ints.\n");
    return 0;
  }
  j = array[0];
  for (i=1; i<sizeof(array); i++)
    if (array[i] > j)
      j = array[i];
  return j;
}

int mini(int *array) {
  int i, j;
  if (!sizeof(array)) {
    notify_fail("Array must contain one or more ints.\n");
    return 0;
  }
  j = array[0];
  for (i=1; i<sizeof(array); i++)
    if (array[i] < j)
      j = array[i];
  return j;
}
