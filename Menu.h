void Menu::playSelected() {
    Clear Clear;
    Clear.clear();

    ifstream OPEN_SCREEN_RES;
    OPEN_SCREEN_RES.open("./res/op/scr/screen_res.txt");

    unsigned short int WIDTH;
    unsigned short int HEIGHT;

    OPEN_SCREEN_RES >> WIDTH >> HEIGHT;
    try {
        for (signed short int i = 0; i < WIDTH / 27; i++)
            std::cout << " ";
        std::cout << "|---------------|" << endl;
        for (signed short int i = 0; i < WIDTH / 27; i++)
            std::cout << " ";
        std::cout << "| >   Play   <  |" << endl;
        for (signed short int i = 0; i < WIDTH / 27; i++)
            std::cout << " ";
        std::cout << "|    Options    |" << endl;
        for (signed short int i = 0; i < WIDTH / 27; i++)
            std::cout << " ";
        std::cout << "|     Exit      |" << endl;
        for (signed short int i = 0; i < WIDTH / 27; i++)
            std::cout << " ";
        std::cout << "|---------------|" << endl;
        system("PAUSE >NULL");

        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            exitSelected();
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            optionsSelected();
        }
        else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {

        }
        else {
            throw 1;
        }
    }
    catch (int e) {
        Menu::playSelected();
    }
}