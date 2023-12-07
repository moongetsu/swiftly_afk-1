#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/commands.h>

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Commands *commands = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);

    server = new Server();
    g_playerManager = new PlayerManager();
    commands = new Commands(pluginName);
}

void Command_AFK(int playerID, const char **args, uint32_t argsCount, bool silent)
{
    Player *player = g_playerManager->GetPlayer(playerID);
    if (!player)
        return;
    int team = player->team->Get();
    player->team->Set(TEAM_SPECTATOR);
    player->SendMsg(HUD_PRINTTALK, "{red}[1TAP] {default}You have gone {red}AFK.");
} // "Parca acum arata mai ok 🤓 - Skuzzi (04.12.2023, 21:28)"

void OnPluginStart()
{
    commands->Register("afk", reinterpret_cast<void *>(&Command_AFK));
}

void OnPluginStop()
{

}

const char *GetPluginAuthor()
{
    return "blu, moongetsu";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginName()
{
    return "AFK Plugin";
}

const char *GetPluginWebsite()
{
    return "";
}
