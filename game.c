#include "game.h"

Tile createTile(int y, int x) {
    Tile Tile;
    Tile.isAlive = 1;                       // By default, when the board is generated, all tiles are "alive" (ie not melted)
    Tile.fish = (rand() % 3) + 1;           // Fishes are generated randomly between 1 and 3 (see game rules)
    Tile.isTherePlayer = 0;
    Tile.posX = x;
    Tile.posY = y;
    Tile.isRed = 0;
    return Tile;
}

Tile **createBoard() {
    Tile **board;
    int x = startTilesTabX;                 // x origin of the first tile in the board
    int y = startTilesTabY;                 // y origin of the first tile in the board

    board = malloc(c * sizeof(Tile *));     // Tab 2D of Tiles
    if (!board) {                           // If board == NULL || NB : this notation will often be used
        exit(2);
    }

    for (int i = 0; i < l; ++i) {           // y <=> line
        board[i] = malloc(l * sizeof(Tile));    // Tab of Tiles <=> the line of the tab
        if (!board[i]) {
            exit(2);
        }
        for (int j = 0; j < c; ++j) {       // x <=> columns
            // Now we can generate Tile inside this tab of tab
            if (i % 2 == 0) {               // "Even" line
                board[i][j] = createTile(y + i * tileHeight - 1, x + j * tileWidth);
            } else {                        // "Odd" line
                board[i][j] = createTile(y + i * tileHeight - 1, x + 4 + j * tileWidth);
            }
            // We are doing this because we have to generate a hexagonal board
            // So one line in two have to be shifted slightly to the right
        }
        //y -= 1;                             // Reduce distance between tiles
    }
    return board;
}

int PenguinsPerPlayer(int n) {
    int nbPenguins = 0;
    switch (n) {
        case 2:                                 // 2 players = 4 penguins per player (see game rules)
            nbPenguins = 4;
            break;
        case 3:                                 // 3 players = 3 penguins per player
            nbPenguins = 3;
            break;
        case 4:                                 // 4 players = 2 penguins per player
            nbPenguins = 2;
            break;
        case 5:                                 // 5 players = 1 penguins per player, no need to break twice if we have 5 or 6 the opérations is the same
            nbPenguins = 1;
        case 6:                                 // 6 players = 1 penguins per player
            nbPenguins = 1;
            break;
        default:                                // If we have a value not between 2 and 6 its bug the game should close
            exit(5);
    }
    return nbPenguins;
}

Penguin createPenguin(Tile **board, int color) {
    int randX, randY;
    Penguin penguin;

    if(!board){
        exit(1);
    }

    // Penguins are spawning randomly on the game board  
    randX = rand() % 9;
    randY = rand() % 9;

    // Here, we are testing if there is already penguins at the coords we generated
    while (board[randY][randX].isTherePlayer != 0) {
        randX = rand() % 9;
        randY = rand() % 9;
    }

    // At this point, we found a Tile where there is no penguin that has already been generated, so we tell the board that there is now a player on this tile
    board[randY][randX].isTherePlayer = 1;

    // Penguins coords = coords we generated
    penguin.tileX = randX;
    penguin.tileY = randY;

    penguin.color = color;                          // We give a color to this penguin
    board[randY][randX].penguinColor = color;       // At this random Tile without penguin, we assign the color of the penguin
    penguin.isMoveable = 1;                         // By default, at the beginning of the game, a penguin is moveable

    return penguin;
}

Player *createTabPlayers(Tile **board, int nbPlayer) {
    int nbPenguin = 0;               // nbPenguin = numbers of penguins per player
    unsigned long length;           // Len of player name
    char name[100];
    Player *tabPlayers;                 // tab of players

    if(!board){
        exit(1);
    }

    while (nbPlayer < 2 || nbPlayer > 6) {
        scanf("%d", &nbPlayer);
    }
    tabPlayers = malloc(nbPlayer * sizeof(Player));            // Tab of nbPlayer players
    if (!tabPlayers) {
        exit(1);
    }

    nbPenguin = PenguinsPerPlayer(nbPlayer);

    // Going through this tab and ask for the name of each player
    for (int i = 0; i < nbPlayer; ++i) {
        do{
            printf("Enter the name of the player %d :\n", i + 1); // Print this message in the window
            scanf("%s", name);
            length = strlen(name);
        }while(length == 0);

        // We use dynamic allocation for the player's name
        tabPlayers[i].name = malloc(length+1 * sizeof(char));// +1 to get the end line character
        if (!tabPlayers[i].name) {
            exit(1);
        }

        tabPlayers[i].penguin = malloc(PenguinsPerPlayer(nbPlayer) * sizeof (Penguin));
        if (!tabPlayers[i].penguin) {
            tabPlayers[i].penguin = malloc(nbPenguin * sizeof(Penguin));
            exit(1);
        }

        // Attribution of the player's number and name
        tabPlayers[i].num = i;
        strcpy(tabPlayers[i].name, name);

        // Creating all penguins for each player
        for (int j = 0; j < nbPenguin; ++j) {
            tabPlayers[i].penguin[j] = createPenguin(board, i + 1);
        }
        tabPlayers[i].currentPenguins = 0;              // By default, we initialize at 0 to avoid some bug
        tabPlayers[i].score = 0;                        // By default, each player have 0 points
        tabPlayers[i].canPlay = 1;                      // By default, each player can play
    }

    return tabPlayers;
}

void showTile(Tile tile, Player *player, int nbPlayer) {     // Print a "tile" with the coordinates stored in the "Tile" parameter
    if (tile.isAlive == 0) {
        printf("XX ");
        return;
    }

    if (tile.isTherePlayer) {
        printf("P%d ", tile.penguinColor);
    } else {
        printf("F%d ", tile.fish);
    }
}

void showIceFloe(Tile **board, Player *player, int nbPlayer) {              // Shows the ice floe and score
    if(!player || !board){
        exit(1);
    }
    
    for (int i = 0; i < l; i++) { // Loop over the number of lines
        for (int j = 0; j < c; j++) { // Loop over the number of columns of rows
            showTile(board[i][j], player, nbPlayer); // We print the tile using the data stored in board
        }
        printf("\n");
    }

    // At each frame, the score for each player is updated
    printf("Score:\n");
    for (int i = 0; i < nbPlayer; ++i) {
        printf("%s: %d\n", player[i].name, player[i].score);
    }
}

int tileDontExist(int y, int x) {       // If tile don't exist, return 0. Else, return 1
    if (x > c-1 || x < 0 || y > l-1 || y < 0) {
        return 1;
    } else {
        return 0;
    }
}

void movePenguin(Tile **board, Player *player, Penguin *virtualPenguin, int touch, int nbPlayer, int movementNb, int* retry, int currentPlayer, int turn) {
    int n = 0;                                          // n is a variable for moving from an iceberg to another
    int isBlocked = 0;                                  // Can the penguin move? (If the next tile is either not on the board, dead or taken by another penguin) 
    int initialPosX = virtualPenguin->tileX;            // Save the original x position of the virtual penguin
    int initialPosY = virtualPenguin->tileY;            // Save the original y position of the virtual penguin

    if(!board || !player || !virtualPenguin || !retry){
        exit(1);
    }

    switch (touch) {
        case 'a':
            while(n < movementNb && !isBlocked){
                if(virtualPenguin->tileX == 0){
                    if (tileDontExist(virtualPenguin->tileY - 1, virtualPenguin->tileX) ||
                        board[virtualPenguin->tileY - 1][virtualPenguin->tileX].isAlive == 0 ||
                        board[virtualPenguin->tileY - 1][virtualPenguin->tileX].isTherePlayer == 1) {
                        isBlocked = 1;
                    }
                    else {
                        virtualPenguin->tileY = virtualPenguin->tileY - 1;
                        virtualPenguin->tileX = virtualPenguin->tileX;
                    }
                }
                else{
                    if (virtualPenguin->tileY % 2 == 0) {    //"even" line
                        if (tileDontExist(virtualPenguin->tileY - 1, virtualPenguin->tileX - 1) ||
                            board[virtualPenguin->tileY - 1][virtualPenguin->tileX - 1].isAlive == 0 ||
                            board[virtualPenguin->tileY - 1][virtualPenguin->tileX - 1].isTherePlayer == 1) {
                            isBlocked = 1;
                        }
                        else {
                            virtualPenguin->tileY = virtualPenguin->tileY - 1;
                            virtualPenguin->tileX = virtualPenguin->tileX - 1;
                        }
                    }
                    else {
                        if (tileDontExist(virtualPenguin->tileY - 1, virtualPenguin->tileX) ||
                            board[virtualPenguin->tileY - 1][virtualPenguin->tileX].isAlive == 0 ||
                            board[virtualPenguin->tileY - 1][virtualPenguin->tileX].isTherePlayer == 1) {
                            isBlocked = 1;
                        }
                        else {
                            virtualPenguin->tileY = virtualPenguin->tileY - 1;
                            virtualPenguin->tileX = virtualPenguin->tileX;
                        }
                    }
                }
                n++;
            }
            break;
        case 'e':
            while(n < movementNb && !isBlocked){
                if (virtualPenguin->tileY % 2 == 0) {
                    if (tileDontExist(virtualPenguin->tileY - 1, virtualPenguin->tileX) ||
                        board[virtualPenguin->tileY - 1][virtualPenguin->tileX].isAlive == 0 ||
                        board[virtualPenguin->tileY - 1][virtualPenguin->tileX].isTherePlayer == 1) {
                        isBlocked = 1;
                    } else {
                        virtualPenguin->tileY = virtualPenguin->tileY - 1;
                        virtualPenguin->tileX = virtualPenguin->tileX;
                    }
                }
                else {
                    if (tileDontExist(virtualPenguin->tileY, virtualPenguin->tileX + 1) ||
                        board[virtualPenguin->tileY - 1][virtualPenguin->tileX + 1].isAlive == 0 ||
                        board[virtualPenguin->tileY - 1][virtualPenguin->tileX + 1].isTherePlayer == 1) {
                        isBlocked = 1;
                    }
                    else {
                        virtualPenguin->tileY = virtualPenguin->tileY - 1;
                        virtualPenguin->tileX = virtualPenguin->tileX + 1;
                    }
                }
                n++;
            }
            break;
        case 'q':
            while(n < movementNb && !isBlocked){
                if (tileDontExist(virtualPenguin->tileY, virtualPenguin->tileX - 1) ||
                    board[virtualPenguin->tileY][virtualPenguin->tileX - 1].isAlive == 0 ||
                    board[virtualPenguin->tileY][virtualPenguin->tileX - 1].isTherePlayer == 1) {
                    isBlocked = 1;
                }
                else {
                    virtualPenguin->tileY = virtualPenguin->tileY;
                    virtualPenguin->tileX = virtualPenguin->tileX - 1;
                }
                n++;
            }
            break;
        case 'd':
            while(n < movementNb && !isBlocked){
                if (tileDontExist(virtualPenguin->tileY, virtualPenguin->tileX + 1) ||
                    board[virtualPenguin->tileY][virtualPenguin->tileX + 1].isAlive == 0 ||
                    board[virtualPenguin->tileY][virtualPenguin->tileX + 1].isTherePlayer == 1) {
                    isBlocked = 1;
                }
                else {
                    virtualPenguin->tileY = virtualPenguin->tileY;
                    virtualPenguin->tileX = virtualPenguin->tileX + 1;
                }
                n++;
            }
            break;
        case 'w':
            while(n < movementNb && !isBlocked){
                if(virtualPenguin->tileY == 8 && movementNb > 0){
                    isBlocked = 1;
                }
                else{
                    if (virtualPenguin->tileX == 0) {
                        if (tileDontExist(virtualPenguin->tileY + 1, virtualPenguin->tileX) ||
                            board[virtualPenguin->tileY + 1][virtualPenguin->tileX].isAlive == 0 ||
                            board[virtualPenguin->tileY + 1][virtualPenguin->tileX].isTherePlayer == 1) {
                            isBlocked = 1;
                        }
                        else {
                            virtualPenguin->tileY = virtualPenguin->tileY + 1;
                            virtualPenguin->tileX = virtualPenguin->tileX;
                        }
                    }
                    else{
                        if (virtualPenguin->tileY % 2 == 0) { // Handling even lines
                            if (tileDontExist(virtualPenguin->tileY + 1, virtualPenguin->tileX - 1) ||
                                board[virtualPenguin->tileY + 1][virtualPenguin->tileX - 1].isAlive == 0 ||
                                board[virtualPenguin->tileY + 1][virtualPenguin->tileX - 1].isTherePlayer == 1) {
                                isBlocked = 1;
                            }
                            else {
                                virtualPenguin->tileY = virtualPenguin->tileY + 1;
                                virtualPenguin->tileX = virtualPenguin->tileX - 1;
                            }
                        }
                        else {
                            if (tileDontExist(virtualPenguin->tileY + 1, virtualPenguin->tileX) ||
                                board[virtualPenguin->tileY + 1][virtualPenguin->tileX].isAlive == 0 ||
                                board[virtualPenguin->tileY + 1][virtualPenguin->tileX].isTherePlayer == 1) {
                                isBlocked = 1;
                            }
                            else {
                                virtualPenguin->tileY = virtualPenguin->tileY + 1;
                                virtualPenguin->tileX = virtualPenguin->tileX;
                            }
                        }
                    }
                }
                n++;
            }
            break;
        case 'c':
            while(n < movementNb && !isBlocked){
                if(virtualPenguin->tileY == 8 && movementNb > 0){
                    isBlocked = 1;
                }
                else{
                    if (virtualPenguin->tileY % 2 == 0) {
                        if (tileDontExist(virtualPenguin->tileY + 1, virtualPenguin->tileX) ||
                            board[virtualPenguin->tileY + 1][virtualPenguin->tileX].isAlive == 0 ||
                            board[virtualPenguin->tileY + 1][virtualPenguin->tileX].isTherePlayer == 1) {
                            isBlocked = 1;
                        }
                        else {
                            virtualPenguin->tileY = virtualPenguin->tileY + 1;
                            virtualPenguin->tileX = virtualPenguin->tileX;
                        }
                    }
                    else {
                        if (tileDontExist(virtualPenguin->tileY + 1, virtualPenguin->tileX + 1) ||
                            board[virtualPenguin->tileY + 1][virtualPenguin->tileX + 1].isAlive == 0 ||
                            board[virtualPenguin->tileY + 1][virtualPenguin->tileX + 1].isTherePlayer == 1) {
                            isBlocked = 1;
                        }
                        else {
                            virtualPenguin->tileY = virtualPenguin->tileY + 1;
                            virtualPenguin->tileX = virtualPenguin->tileX + 1;
                        }
                    }
                }
                n++;
            }
            break;
        default :
            *retry = 1;
            break;
    }

    if(isBlocked == 1){                         // if the penguin is blocked (ie the movement wanted by user is impossible)
        *retry = 1;                             // the user will have to choose another movement
        printf("This move isn't valid, please choose another move.\n");
        virtualPenguin->tileY = initialPosY;
        virtualPenguin->tileX = initialPosX;
    }
}

void Score(Player *player, Tile *tile) {        // Add fishes collected by the player to his points
    player->score += tile->fish;
}

int simple(Tile** board, Penguin penguin, int y, int x) { // To make the code more readable, we have separated the conditions into several functions
    if(!board){
        exit(1);
    }
    if (tileDontExist(penguin.tileY + y, penguin.tileX + x) ||
        board[penguin.tileY + y][penguin.tileX + x].isAlive == 0 ||
        board[penguin.tileY + y][penguin.tileX + x].isTherePlayer == 1) {
        return 1;
    } else {
        return 0;
    }
}

int isPenguinMoveable(Tile** board, Penguin penguin){
    if(!board){
        exit(1);
    }

    if (penguin.tileY % 2 == 0) { // Conditions on even-numbered lines
        if (simple(board, penguin, -1, 0) && simple(board, penguin, -1, +1) && simple(board, penguin, 0, -1) &&
            simple(board, penguin, 0, +1) && simple(board, penguin, +1, 0) && simple(board, penguin, -1, +1)) {
            return 0;
        }
        else{
            return 1;
        }
    } else { // Conditions on odd-numbered lines
        if (simple(board, penguin, -1, -1) && simple(board, penguin, -1, 0) && simple(board, penguin, 0, -1) &&
            simple(board, penguin, 0, +1) && simple(board, penguin, +1, -1) && simple(board, penguin, -1, 0)) {
            return 0;
        }
        else{
            return 1;
        }
    }
}

int isAllPlayerBlocked(Tile** board, Player* player, int nbPlayer){
    if(!board || !player){
        exit(1);
    }
    int blockedCount = 0;
    for (int i = 0; i < nbPlayer; ++i) {
        for (int j = 0; j < PenguinsPerPlayer(nbPlayer); ++j) {
            if(isPenguinMoveable(board, player[i].penguin[j])){
                player[i].penguin[j].isMoveable = 1;
            }
            else{
                player[i].penguin[j].isMoveable = 0;
                blockedCount++;
            }
            if ((blockedCount % 4) == PenguinsPerPlayer(nbPlayer)){
                player[i].canPlay = 0;
            }
        }
    }
    if( blockedCount == nbPlayer * PenguinsPerPlayer(nbPlayer)){
        return 1;
    }
    else{
        return 0;
    }
}

void Winners(Player *player, int SIZE){
    if(!player){
        exit(1);
    }
    int j = 0;
    int nbWinner = 0;
    Player win = player[0];

    Player* winners = malloc(SIZE * sizeof(Player));
    if(winners == NULL){
        exit(-1);
    }

    for(int i = 1; i < SIZE; i++){
        if(win.score < player[i].score){
            win = player[i];
    }
    winners[j] = win;
    j++;
        nbWinner += 1;

    for(int k = 1; k < SIZE; k++){
            winners[j] = player[k];
            nbWinner++;
        }
    }

    if(nbWinner == 1){
        printf("The winner is %s\n", winners[0].name);
    }
    else{
        printf("The winners are:\n");
        for(int i = 0; i < nbWinner; i++){
            printf("%s\n", winners[i].name);
        }
    }
}

void Game(Tile **board, int* rematch) {
    if(!board || rematch==NULL){
        exit(1);
    }
    int touch;
    int turn = 0;
    int currentPlayer = 0;
    int nbPlayer;
    int selectedPenguinNb;
    int impossibleSelection;
    int nbPenguin;
    int disableL;
    int passK = 0;
    int returnMenu = 0;
    Player *player;
    do{
        printf("How many players? (between 2 and 6) press enter after you press the number\n");
        scanf("%d", &nbPlayer);
    }while(nbPlayer<2 || nbPlayer>6);

    player = createTabPlayers(board, nbPlayer);
    nbPenguin = PenguinsPerPlayer(nbPlayer);

    while (!isAllPlayerBlocked(board, player, nbPlayer) && !returnMenu) {
        if(player[currentPlayer].canPlay){
            showIceFloe(board, player, nbPlayer);
            printf("Turn: %d\n", turn);
            printf("Player %d: %s\n", currentPlayer+1, player[currentPlayer].name);
            for (int i = 0; i < nbPenguin; ++i) {
                if(player[currentPlayer].penguin[i].isMoveable){
                    printf("Penguin %d: in y: %d, x: %d\n", i + 1,
                             player[currentPlayer].penguin[i].tileY + 1, player[currentPlayer].penguin[i].tileX +1);
                }
                else{
                    printf("Penguin %d: in y: %d, x: %d NOT MOVEABLE\n", i + 1, player[currentPlayer].penguin[i].tileY+1, player[currentPlayer].penguin[i].tileX+1);
                }
            }
            printf("Choose Your Penguin: ");

            do {
                touch = getchar();
                switch (touch) {
                    case 'y':
                        if(player[currentPlayer].penguin[0].isMoveable == 1){
                            selectedPenguinNb = 0;
                            impossibleSelection = 0;
                        }
                        else{
                            impossibleSelection = 1;
                        }
                        break;
                    case 'u':
                        if(player[currentPlayer].penguin[1].isMoveable == 1){
                            selectedPenguinNb = 1;
                            impossibleSelection = 0;
                        }
                        else{
                            impossibleSelection = 1;
                        }
                        break;
                    case 'i':
                        if(player[currentPlayer].penguin[2].isMoveable == 1){
                            selectedPenguinNb = 2;
                            impossibleSelection = 0;
                        }
                        else{
                            impossibleSelection = 1;
                        }
                        break;
                    case 'o':
                        if(player[currentPlayer].penguin[3].isMoveable == 1){
                            selectedPenguinNb = 3;
                            impossibleSelection = 0;
                        }
                        else{
                            impossibleSelection = 1;
                        }
                        break;
                    default:
                        break;
                }
            } while ((touch != 'y' && touch != 'u' && touch != 'i' && touch != 'o' || selectedPenguinNb > nbPenguin || impossibleSelection) && !returnMenu);

            printf("You chose the penguin %d\n", selectedPenguinNb+1);
            Penguin virtualPenguin = player[currentPlayer].penguin[selectedPenguinNb];

            if(!returnMenu){
                int movementNb;
                char direction;
                printf("Enter the direction (a, e, q, d, w, c) and the number of movements (1-6): ");
                scanf(" %c %d", &direction, &movementNb); // Read direction and movement number
                movePenguin(board, player, &virtualPenguin, direction, nbPlayer, movementNb, &impossibleSelection, currentPlayer, turn);

                if (!impossibleSelection) {
                    board[player[currentPlayer].penguin[selectedPenguinNb].tileY][player[currentPlayer].penguin[selectedPenguinNb].tileX].isTherePlayer = 0;
                    board[player[currentPlayer].penguin[selectedPenguinNb].tileY][player[currentPlayer].penguin[selectedPenguinNb].tileX].isAlive = 0;

                    player[currentPlayer].penguin[selectedPenguinNb] = virtualPenguin;
                    Score(&player[currentPlayer], &board[virtualPenguin.tileY][virtualPenguin.tileX]);

                    board[virtualPenguin.tileY][virtualPenguin.tileX].isTherePlayer = 1;
                    board[virtualPenguin.tileY][virtualPenguin.tileX].penguinColor = currentPlayer + 1;
                } else {
                    printf("Invalid move. Please try again.\n");
                }
            }
        }
        currentPlayer = (currentPlayer + 1) % nbPlayer;
        turn++;
    }
    if(!returnMenu){
        Winners(player, nbPlayer-1);
    }

    do{
        printf("Press 1 if you want to rematch or press 2 if you want to leave the game, then press Enter\n");
        scanf("%d", rematch);
    }while(*rematch !=1 && *rematch !=2);
}

int main() {
    int nbPlayer;
    int rematch = 0;
    Tile **board = NULL;
    Player *players = NULL;

    srand(time(NULL));

    do{
        board = createBoard();
        Game(board, &rematch);
    } while (rematch == 1);

    free(players);
    free(board);
    return 0;
}
