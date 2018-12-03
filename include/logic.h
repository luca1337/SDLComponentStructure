#ifndef LOGIC_H
#define LOGIC_H

typedef struct game_manager{
    void(*init)(struct game_manager*);
    void(*tick)(struct game_manager*);
}game_manager_t;

game_manager_t* game_manager_new();

#endif