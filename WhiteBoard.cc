#include "WhiteBoard.h"
#include "ProjectManager.h"
#include "TempBackground.h"

WhiteBoard::WhiteBoard()
{
    windowManager = new GL_SDL_WindowManager();
    eventDispatcher = new SDLEventDispatcher();
    eventDispatcher->setEventHandler(this);
    screenWidth = 800;
    screenHeight = 600;
    frustum = new Frustum(screenWidth, screenHeight, .45, 1, 5000);
    userQuit = false;
}

void WhiteBoard::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WhiteBoard::addString(string s)
{
    strings.push_back(s);

    TextModel *textModel = new TextModel(s.c_str(), 30);
    textModel->setPosition(0, 0);
    textModels.push_back(textModel);
}

void WhiteBoard::keyPressed()
{
    userQuit = true;
}

void WhiteBoard::run()
{
    string uname;
    string pword;
    cout << "username?\n";
    cin >> uname;
    cout << "password?\n";
    cin >> pword;

    this->uname = uname;
    this->pword = pword;

    windowManager->createWindow(screenWidth, screenHeight);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);

    vector<float> values = frustum->getProjectionMatrix();

    init_background();

    addString("The following is the list of current projects:");

    ProjectManager projects;
    projects.fetchProjects(this);

    float matrix[16];
    std::copy(values.begin(), values.end(), matrix);
    glMultMatrixf(matrix);

    long previousTickCount = 0;

    while (1) {
        long currentTickCount = SDL_GetTicks();
        long ticksSinceLastFrame = currentTickCount - previousTickCount;
        previousTickCount = currentTickCount;

        int framesPerSecons = 1000L / ticksSinceLastFrame;

        eventDispatcher->pollEvents();

        if (userQuit)
            break;

        clearScreen();

        draw_background();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float x = -.58;
        float y = .44;

        for (int i = 0; i < strings.size(); ++i)
        {
            TextModel *textModel = textModels[i];
            textModel->setPosition(x, y);
            y -= .04;
            textModel->draw();
        }

        windowManager->swapBuffers();
    }

    SDL_Quit();
}

// END OF FILE
