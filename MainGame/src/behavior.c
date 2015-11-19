#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/character.h"
#include "../include/behavior.h"

void FlyingBehavior(CharacterType *selfType, int self_index, CharacterType *targetType, int target_index) {
	CharacterTraits *self = selfType->character_traits + self_index;
/*
	if (self.x - player.x > 300) { // move to 300 away from character in the x
		self->acceleration.x -= 1;
	}
	// self.x - player.x < -300 
	else if ( - self.x < 300) {
		self->acceleration.x += 1;
	} else {
		self->acceleration.x *= 0.9;
		if (self->acceleration.x < 0.05) {
			self->acceleration.x = 0;
		}
		// if almost 0 set to 0, do that in update
	}
*/
	// the swooping
	// if self.x is greater than player.x, self.accel.x = -1;
	// if self.x is less than player.x, self.accel.x = 1;
	// if self.y is less than player.y, self.accel.y = 1;
	// if self.y is greater than player.y, self.accel.y = 1;
	// wait A seconds between each swoop

}
