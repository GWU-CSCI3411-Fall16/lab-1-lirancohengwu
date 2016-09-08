#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

char* titles[] = {"Give You Up", "Stairway to Heaven"};
char* singers[] = {"Rick Astley", "Led Zepplin"};

typedef int (*compare_f)(void*, void*);

struct playlist_t {
    struct node_t* head;
    compare_f comparison;
};

struct song_t {
  char* title;
  char* singer;
};

struct node_t {
  struct song_t* song;
  struct node_t* next;
};

int are_two_songs_same(void* song1, void* song2) {
    struct song_t* s1 = (struct song_t*) song1;
    struct song_t* s2 = (struct song_t*) song2;
    if (strcmp(s1->title, s2->title) != 0) return 0;
    if (strcmp(s1->singer, s2->singer) != 0) return 0;
    return 1;
}

struct playlist_t* pl_create(void) {
    struct playlist_t* pl;
    pl = (struct playlist_t*)malloc(sizeof(struct playlist_t));
    if (pl == NULL) return NULL;
    pl->head = NULL;
    pl->comparison = NULL;
    return pl;
}

void pl_destroy(struct playlist_t* pl) {
    assert(pl != NULL);
    assert(pl->head != NULL);
    free(pl);
}

struct node_t* node_create(void* data) {
    struct node_t* node;
    node = (struct node_t*)malloc(sizeof(struct node_t));
    if (node == NULL) return NULL;
    node->song = data;
    node->next = NULL;
    return node;
}

void node_destroy(struct node_t* node) {
    assert(node != NULL);
    free(node);
}

//adds to end of list
void pl_add(struct playlist_t*  pl, void* data) {
    struct node_t* ptr;
    struct node_t* node;
    
    assert(pl != NULL);
    node = node_create(data);
    assert(node != NULL);
    
    if (pl->head == NULL){
        pl->head = node;
    } else {
        ptr = pl->head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = node;
    }
}

void* pl_remove_first(struct playlist_t*  pl) {
    void* data;
    struct node_t* head;
    assert(pl != NULL);
    head = pl->head;
    if (head == NULL) {
        return NULL;
    }
    pl->head = head->next;
    data = head->song;
    node_destroy(head);
    return data;
}

int pl_contains(struct playlist_t* pl, void* value) {
    struct node_t* ptr;
    int pos = 0;
    
    assert(pl != NULL);
    
    ptr = pl->head;
    while (ptr != NULL) {
        pos++;
        if (pl->comparison == NULL) {
            //Lazy comparison
            if (ptr->song == value) {
                return pos;
            }
        } else {
            //Custom true comparison
            if (pl->comparison(ptr->song, value)) {
                return pos;
            }
        }
        ptr = ptr->next;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    struct song_t song_1, song_2;
    struct node_t *node_1, *node_2;
    
    struct playlist_t* pl;
    pl = pl_create();
    assert(pl != NULL);
    pl->comparison = &are_two_songs_same;
  
    song_1.title = titles[0];
    song_1.singer = singers[0];

    song_2.title = titles[1];
    song_2.singer = singers[1];
    
    pl_add(pl, &song_1);
    pl_add(pl, &song_2);
    
    pl_destroy(pl);

    return 0;
}
