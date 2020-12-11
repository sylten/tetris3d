#include "player.h"

#include "..\main\constants.h"
#include "..\main\key_names.h"
#include "..\misc\megazor.h"

Player::Player(CubeContainer *cont)
{
    container = cont;

    current.setType(CubeColor(rand()%7));
    preview.setType(CubeColor(rand()%7));
    current.setPos(BOARD_WIDTH / 2 - 1, -3);

    //Initiera spelplanen (Inga kuber utplacerade)
    for (int ix = 0; ix < BOARD_WIDTH; ix++)
        for (int iy = 0; iy < BOARD_HEIGHT; iy++)
            board[ix][iy] = NO_CUBE;

    tickFull = TICK_START;
    tickTime = tickFull;
    level = 1;
    lines = 0;
    score = 0;
    failed = false;

    rotateKey = SE_UP;
    leftKey = SE_LEFT;
    rightKey = SE_RIGHT;
    downKey = SE_DOWN;
    useKey = SE_SPACE;
}

string Player::getLevelStr() const
{
    return I2S(level);
}
string Player::getScoreStr() const
{
    return I2S(score);
}
string Player::getLinesStr() const
{
    return I2S(lines);
}
bool Player::hasFailed() const
{
    return failed;
}

void Player::handleInput(KeyboardListener *keyboard)
{
    if (!failed)
    {
        if (keyboard->wasPressed(rotateKey)) //Rotera med upp
            current.rotate(board);
        if (keyboard->wasPressed(leftKey)) //Flytta höger med högerpil
            current.move(-1, 0, board);
        if (keyboard->wasPressed(rightKey)) //Flytta vänster med vänsterpil
            current.move(1, 0, board);
        if (keyboard->wasPressed(downKey)) //Skicka längst ner med nerpil
        {
            MoveResult mr = NOTHING;
            while(mr == NOTHING)
                mr = current.move(0, 1, board); //Flytta ner blocket 1 steg i taget tills den träffar något

            if (mr == FAIL)
                failed = true;

            score += 1; //Ge spelaren 1 poäng per steg
            tickTime = 0.0f;
        }
    }
}

void Player::advanceLogic(float elapsedTime)
{
    tickTime -= elapsedTime;
    if (tickTime <= 0.0f && !failed)
    {
        MoveResult mr = current.move(0, 1, board);

        if (mr == NEW)
        {
            current = preview;
            preview.setType(CubeColor(rand()%7));
            current.setPos(BOARD_WIDTH / 2 - 1, -3);
        }
        else if (mr == FAIL)
            failed = true;

        //Kolla om några rader är fulla
        int amnt = 0;
        for(int iy = 1; iy < BOARD_HEIGHT; iy++)
        {
            int filledY = iy;
            for(int ix = 1; ix < BOARD_WIDTH; ix++)
                if(board[ix][iy] == NO_CUBE)
                    filledY = -1;

            if(filledY != -1)
            {
                for(int x = 0; x < BOARD_WIDTH; x++)
                {
                    container->add(CubeColor(board[x][filledY]),
                                   D3DXVECTOR3(x * CUBE_LENGTH, filledY * CUBE_LENGTH, 0.0f));

                    for(int y = filledY; y > 0; y--)
                        board[x][y] = board[x][y-1];
                }
                amnt++;
                lines++;
                if (level < 9 && lines%10 == 0) //Öka leveln var 10e rad
                {
                    level++;
                    tickFull -= TICK_DECREASE;
                }
            }
        }
        //Ge poäng om man fyllt hela rader
        switch(amnt)
        {
            case 1: score += (level + 1) * 40; break;
            case 2: score += (level + 1) * 100; break;
            case 3: score += (level + 1) * 300; break;
            case 4: score += (level + 1) * 1200; break;
        }

        tickTime = tickFull;
    }
}

void Player::render(int a, GameProps *props, LPDIRECT3DDEVICE9 d3dDevice)
{
    //Rendera det fallande blocket
    current.render(props->cubes[current.getCubeId()], d3dDevice);
    //Rendera förhandsvisningen av nästa block
    preview.render(props->cubes[preview.getCubeId()], d3dDevice);

    props->borders[HORIZONTAL]->render(D3DXVECTOR3(0.5f, 0.51f, 0.0f), d3dDevice);
    props->borders[HORIZONTAL]->render(D3DXVECTOR3(0.5f, 50.0f, 0.0f), d3dDevice);
    props->borders[VERTICAL]->render(D3DXVECTOR3(0.5f, 0.5f, 0.0f), d3dDevice);
    props->borders[VERTICAL]->render(D3DXVECTOR3(26.0f, 0.5f, 0.0f), d3dDevice);

    //Rendera ramen samt alla block på spelplanen
    for (int ix = 0; ix < BOARD_WIDTH; ix++)
        for (int iy = 0; iy < BOARD_HEIGHT; iy++)
            if (board[ix][iy] != NO_CUBE)
                props->cubes[board[ix][iy]]->render(D3DXVECTOR3(ix * CUBE_LENGTH, iy * CUBE_LENGTH, 0.0f), d3dDevice);

    props->txt->show("Level: ", STATS_SMALL, 255, 204, 0, a, 680, 230);
    props->txt->show("Lines: ", STATS_SMALL, 255, 204, 0, a, 680, 250);
    props->txt->show("Score: ", STATS_SMALL, 255, 204, 0, a, 680, 270);
    props->txt->show(getLevelStr(), STATS_SMALL, 255, 204, 0, a, 740, 230);
    props->txt->show(getLinesStr(), STATS_SMALL, 255, 204, 0, a, 740, 250);
    props->txt->show(getScoreStr(), STATS_SMALL, 255, 204, 0, a, 740, 270);

    if (failed)
    {
        props->txt->show("GAME OVER", STATS_MEDIUM, 255, 204, 0, 255-a, 433, 250);
        props->txt->show("Level: ", STATS_SMALL, 255, 204, 0, 255-a, 475, 300);
        props->txt->show("Lines: ", STATS_SMALL, 255, 204, 0, 255-a, 475, 330);
        props->txt->show("Score: ", STATS_SMALL, 255, 204, 0, 255-a, 475, 360);
        props->txt->show(getLevelStr(), STATS_SMALL, 255, 204, 0, 255-a, 535, 300);
        props->txt->show(getLinesStr(), STATS_SMALL, 255, 204, 0, 255-a, 535, 330);
        props->txt->show(getScoreStr(), STATS_SMALL, 255, 204, 0, 255-a, 535, 360);
    }
}
