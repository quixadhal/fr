/*
 * uid.h
 * Created by: Erik Kay
 * Description: new uid / euid data structures and security
 * Modification:
 *    11-1-92 - Erik Kay - initial creation
 *    94.07.09 - Robocoder - modified to use AVL tree
 */

#ifndef UID_H
#define UID_H

typedef struct _uid {
    char *name;
} userid_t;

userid_t *add_uid PROT((char *name));
userid_t *set_root_uid PROT((char *name));
userid_t *set_backbone_uid PROT((char *name));

#endif
