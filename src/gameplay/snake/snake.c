#include "snake.h"
#include "../../standard/math/point.h"

void snake_grow(snake_t *snake) {
    assert(snake);
    // TODO
}

void snake_diminish(snake_t *snake);

void change_dir(point_t* last_dir, char new_dir){
    if(new_dir == "G" && last_dir->x <= 0 && last_dir->x > -36){//on part du principe que les directions sont modélisées par un cercle de 36 pixels de rayon
        last_dir->x -= 2;
        if(last_dir->y < 0){
            last_dir->y += 2;
        }else{
            last_dir->y -= 2;
        }
    }

    if(new_dir == "D" && last_dir->x >= 0 && last_dir->x < 36){//on part du principe que les directions sont modélisées par un cercle de 36 pixels de rayon
        last_dir->x += 2;
        if(last_dir->y < 0){
            last_dir->y += 2;
        }else{
            last_dir->y -= 2;
        }
    }

    if(new_dir == "H" && last_dir->y <= 0 && last_dir->y > -36){//on part du principe que les directions sont modélisées par un cercle de 36 pixels de rayon
        last_dir->y -= 2;
        if(last_dir->x < 0){
            last_dir->x += 2;
        }else{
            last_dir->x -= 2;
        }
    }

    if(new_dir == "B" && last_dir->y >= 0 && last_dir->y < 36){//on part du principe que les directions sont modélisées par un cercle de 36 pixels de rayon
        last_dir->y += 2;
        if(last_dir->x < 0){
            last_dir->x += 2;
        }else{
            last_dir->x -= 2;
        }
    }

}

void snake_move(snake_t *snake, double direction /* type ? */);

void snake_draw(const snake_t *snake);