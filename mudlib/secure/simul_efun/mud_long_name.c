/* Mud long name.. 
 * Returns a readable version of the muds name.
 * pretty stupid and simple way to do it, shoulud at least check a .h file.
 * Baldrick, dec '96.
 */

string mud_long_name()
  {
  switch (mud_name())
    {
    default: return "Obviously not decided yet";
    }
}
