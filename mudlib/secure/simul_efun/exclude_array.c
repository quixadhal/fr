varargs mixed *exclude_array(mixed *array, int from, int to) {
    mixed *bottom, *top;

    bottom = ({});
    top = ({});
    if(!to) to = from;
    if(from > 0) bottom = array[0..from -1];
    if(to < sizeof(array)-1) top = array[to+1..sizeof(array)-1];
    return bottom + top;
}
