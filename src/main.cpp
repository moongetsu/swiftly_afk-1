#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/database.h>
#include <swiftly/commands.h>
#include <swiftly/configuration.h>
#include <swiftly/logger.h>
#include <swiftly/timers.h>

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Database *db = nullptr;
Commands *commands = nullptr;
Configuration *config = nullptr;
Logger *logger = nullptr;
Timers *timers = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);

    server = new Server();
    g_playerManager = new PlayerManager();
    commands = new Commands(pluginName);
    config = new Configuration();
    logger = new Logger(mainFilePath, pluginName);
    timers = new Timers();
}

void Command_AFK(Player *player)
{
    int team = player->team->Get();

    player->team->Set(TEAM_SPECTATOR);
    player->SendMsg(HUD_PRINTTALK, "{RED}[1TAP]{DEFAULT}You have gone {RED}AFK.");
}

void OnPluginStart()
{
    commands->Register("afk", reinterpret_cast<void *>(&Command_AFK));
}

void OnPluginStop()
{
    timers->UnregisterTimers();
}

const char *GetPluginAuthor()
{
    return "";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginName()
{
    return "swiftly_afk";
}

const char *GetPluginWebsite()
{
    return "";
}