
///////////////////////////////////////////////////////////////////////////////

#include "common.h"

///////////////////////////////////////////////////////////////////////////////

void tile_partitioning() {
	// Partitioning.
	for(u16 ty = 0; ty < TILE_MAT_HEIGHT; ty++){
		for(u16 tx = 0; tx < TILE_MAT_WIDTH; tx++){
			_tile_mat->mat[tx][ty].list_end = 0;
		}
	}

	for(i16 i = _draw_list->list_end-1; i >= 0; i--){
		Rect r = _draw_list->rects[i];
		u16 tx_beg = r.x >> TILE_BITS;
		u16 ty_beg = r.y >> TILE_BITS;
		u16 tx_end = (r.x + r.w) >> TILE_BITS;
		u16 ty_end = (r.y + r.h) >> TILE_BITS;
	
		for(u16 ty = ty_beg; ty <= ty_end; ty++){
			for(u16 tx = tx_beg; tx <= tx_end; tx++){
				TileList* tl = &_tile_mat->mat[tx][ty];
				if(tl->list_end < TILE_LIST_LEN){
					// List is not full.
					tl->list[tl->list_end++] = i;
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
