#ifndef BEHAVIOR_H
#define BEHAVIOR_H

/* Types of behavior for different classes of characters */
void FlyingBehavior(void *self, int self_index, void *player);

void FightingBehavior(void *self, int self_index, void *player);

void RangingBehavior(void *self, int self_index, void *player);

#endif
