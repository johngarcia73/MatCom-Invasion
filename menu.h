int level = 1;
bool nextLevel= false;

void select2();
void mainMenu();
void drawOptions();
void drawPointer();
void erasePointer();
void drawTitle();

void init();   //Initializes the map with start positions
void game();
void* keyListener(void * t);        //Calls Draw function and identifies if user pressed -> or <-, and updates the ship position.
void munition();
void* reload(void* th);
void draw();
void endGame();