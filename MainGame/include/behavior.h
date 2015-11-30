#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "character.h"
#include "player.h"

typedef void (*BehaviorFunction)(CharacterType *self, int self_index, CharacterType *target, int t_index);

/* Types of behavior for different classes of characters */
void FlyingBehavior(CharacterType *self, int self_index, Player *p);

void FightingBehavior(CharacterType *self, int self_index, Player *p);

void RangingBehavior(CharacterType *self, int self_index, Player *p);

#endif
