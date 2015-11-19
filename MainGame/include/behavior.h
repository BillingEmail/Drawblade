#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "character.h"

typedef void (*BehaviorFunction)(CharacterType *self, int self_index, CharacterType *target, int t_index);

/* Types of behavior for different classes of characters, can have a target entity (usually the player) */
void FlyingBehavior(CharacterType *self, int self_index, CharacterType *target, int target_index);

void FightingBehavior(CharacterType *self, int self_index, CharacterType *target, int target_index);

void RangingBehavior(CharacterType *self, int self_index, CharacterType *target, int target_index);

#endif
