#include <stdio.h>

char* titles = {"Give You Up", "Stairway to Heaven"};
char* singers = {"Rick Astley", "Led Zepplin"};

struct song_t {
  char* title;
  char* singer;
};

struct node_t {
  struct song_t* song;
  struct node_t* next;
}

int main(int argc, char* argv[]) {
  struct song_t ricksong, ledsong;
  struct node_t p1_rick, p1_led, p2_rick, p2_led;
  
  ricksong.title = titles[0];
  ricksong.singer = singers[0];

  ledsong.title = titles[1];
  ledsong.singer = singers[1];

  p1_rick.song = &ricksong;
  p1_rick.next = &p1_led;
  p1_led.song = &ledsong;
  p1_led.next = NULL;

  return 0;
}
