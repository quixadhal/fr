
/* The armour_table 
 * Started by Dank, completed by Baldrick.
 */

int *lookup_armour_data(string name) 
  {
  int i;
  int *armour_data;

/* armour data are of form: 
 * 0: gp cost (use negative integer if cost is in silver, i.e. -5 = 5 silver.
 * 1: gp cost of enchanted +1 item, 
 * 2: weight in standard game units (tenths of pounds), 
 * 3: Armor class
 * 4: Type: 1 = bodyarmour, 2 = shield, 3 = helmet, 4 = boots, 5 = amulet, 
 *          6 = cloak, 7 = ring,   8 = gloves 
 * 5: Material: 1 = wood, 2 = metal, 3 = leather, 4 = cloth
 * 
 * Have to add these to the table !!!!! lazy right now.
 * 
 * 6: Holdable. 1 if it is, 0 if it's not.
      If it's holdable, it's not wearable..  
 * 7: 1 if it is of a type that won't give the player a dex modifier on ac.
 *    (like plate armour)
 */

  switch(name) {
    case "banded mail":
    case "banded": 
      armour_data=({ 200,  4000, 350, 7, 1, 2, 0, 0 }); break;

    case "bracers":
      armour_data=({   7,  2000,   5, 0, 1, 2, 0, 0 }); break;

    case "brigandine":
      armour_data=({ 120,  3500, 350, 4, 1, 3, 0, 0 }); break;
     /* The material is leather becuase it's the weakest component.--AKK */

    case "chain mail":
    case "chain":
    case "chainmail":
      armour_data=({  75,  3500, 400, 5, 1, 2, 0, 0 }); break;

    case "bronze plate":
      armour_data=({ 400, 10000, 450, 6, 1, 2, 0, 1 }); break;

    case "elfin chain":
      armour_data=({5000, 20000, 150, 5, 1, 2, 0, 0 }); break;

    case "field plate":
      armour_data=({2000, 15000, 600, 8, 1, 2, 0, 1 }); break;

    case "full plate":
      armour_data=({8000, 30000, 700, 9, 1, 2, 0, 1 }); break;

    case "hide":
      armour_data=({  15,  2500, 300, 4, 1, 3, 0, 0 }); break;

    case "leather":
      armour_data=({   5,  2000, 150, 2, 1, 3, 0, 0 }); break;

    case "padded leather":
    case "padded":
      armour_data=({   4,  2000, 100, 2, 1, 3, 0, 0 }); break;

    case "plate mail":
    case "plate": 
      armour_data=({ 600,  5000, 500, 7, 1, 2, 0, 1 }); break;

    case "ring mail":
      armour_data=({ 100,  3000, 300, 3, 1, 3, 0, 0 }); break;
   /* As with Brigandine, it's leather becuase the leather is the weakest
    * part of the armor. --AKK */

    case "scale mail":
    case "scale":
      armour_data=({ 120,  3500, 400, 4, 1, 3, 0, 0 }); break;
   /* In this case, although leather is the weakest material, the metal scales
    * cover it too well for things to effect the leather. --AKK */

    case "splint mail":
    case "splint":
      armour_data=({  80,  3500, 400, 7, 1, 3, 0, 0 }); break;
   /* Another leather-backed armor.... --AKK */

    case "studded":
    case "studded leather":
      armour_data=({  20,  2000, 250, 3, 1, 3, 0, 0 }); break;

    case "buckler":
      armour_data=({   1,  1500,  30, 1, 2, 2, 1, 0 }); break;

    case "shield":
    case "medium shield":  
      armour_data=({   7,  2500, 100, 1, 2, 2, 1, 0 }); break;

    case "large shield":
      armour_data=({  10,  3000, 150, 1, 2, 2, 1, 0 }); break;

    case "small shield":
      armour_data=({   3,  2000, 120, 1, 2, 2, 1, 0 }); break;

    case "wooden shield":
      armour_data=({   1,  1000,  40, 1, 2, 1, 1, 0 }); break;

    case "helm":
    case "helmet":
    case "basinet":
      armour_data=({   8,  1500,  50, 1, 3, 2, 0, 0 }); break;

    case "cowl":
      armour_data=({   4,  1500,  10, 1, 3, 4, 0, 0 }); break;

    case "great helm":
    case "full helm":
    case "visored helm":
      armour_data=({  30,  2500, 100, 2, 3, 2, 0, 0 }); break;

    case "shoes":
    case "boots":
      armour_data=({   1,  1500,  10, 0, 4, 3, 0, 0 }); break;

    case "slippers":
      armour_data=({   1,  1500,  10, 0, 4, 4, 0, 0 }); break;

    case "amulet":
    case "pendant":
    case "necklace":
      armour_data=({  10,  4000,   2, 0, 5, 2, 0, 0 }); break;

    case "cape":
    case "cloak":
      armour_data=({   1,  1500,  10, 0, 6, 4, 0, 0 }); break;

    case "ring":
      armour_data=({   1,  4000,   1, 0, 7, 2, 0, 0 }); break;

    case "gauntlets":
      armour_data=({   3,  2000,   3, 0, 8, 2, 0, 0 }); break;

    case "gloves":
      armour_data=({   3,  2000,   3, 0, 8, 3, 0, 0 }); break;

    default: break;
  }
  return armour_data;
}
