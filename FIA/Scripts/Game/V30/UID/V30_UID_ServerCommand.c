

class V30_UID_ServerCommand : ScrServerCommand {
    override event string GetKeyword() {
        return "uid";
    };

    override event bool IsServerSide() {
        return false;
    };

    override event protected int RequiredChatPermission() {
        return EPlayerRole.NONE;
    };
    
    override event protected int RequiredRCONPermission() {
		return ERCONPermissions.PERMISSIONS_NONE;
	};

    override event protected ref ScrServerCmdResult OnChatClientExecution(array<string> argv, int playerId) {
        if (argv.Contains("--help"))
            return ScrServerCmdResult(string.Format("Description: print your player UID\nUsage: #%1 [--help | --copy]\nParameter(s): --help - print help message; --copy - copy UID to clipboard (PC only!).", argv.Get(0)), EServerCmdResultType.OK);  

        auto playerUid = GetLocalPlayerUid();
        if (playerUid.IsEmpty())
            return ScrServerCmdResult("Failed to get local player UID!", EServerCmdResultType.ERR);
        
        if (argv.Contains("--copy")) {
            auto platform = System.GetPlatform();
            if (platform == EPlatform.WINDOWS || platform == EPlatform.LINUX)
                System.ExportToClipboard(playerUid);
            else
                PrintFormat("[V30][UID] #uid: trying to copy UID on non-PC platform (%1)!", SCR_Enum.GetEnumName(EPlatform, platform), level: LogLevel.WARNING);
        };

        auto playerName = GetLocalPlayerName();
        auto result = string.Format("%1: %2", playerName, playerUid);
        return new ScrServerCmdResult(result, EServerCmdResultType.OK);
    };

	override event protected ref ScrServerCmdResult OnChatServerExecution(array<string> argv, int playerId) {
        PrintFormat("[V30][UID] #uid: request from player with id = %1", playerId);

        auto playerUid = GetPlayerUid(playerId);
        auto playerName = GetPlayerName(playerId);

        if (playerUid.IsEmpty())
            return ScrServerCmdResult("Failed to get your player UID!", EServerCmdResultType.ERR);

        auto result = string.Format("%1: %2", playerName, playerUid);
        return new ScrServerCmdResult(result, EServerCmdResultType.OK);
    };

    override event protected ref ScrServerCmdResult OnRCONExecution(array<string> argv) {
        return new ScrServerCmdResult("RCON can't have player UID!", EServerCmdResultType.ERR);
    };

    override event protected ref ScrServerCmdResult OnUpdate() {
        return new ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
    };

    protected bool IsPlayerId(string str) {
        if (str.IsEmpty())
            return false;
        auto len = str.Length();
        for (auto i = 0; i < len; i++)
            if (!str.IsDigitAt(i))
                return false;
        return true;
    };

    protected bool IsValidPlayerId(int playerId) {
        return GetAllPlayersIds().Contains(playerId);
    };

    protected array<int> GetAllPlayersIds() {
        auto playerIds = new array<int>();
        GetGame().GetPlayerManager().GetAllPlayers(playerIds);
        return playerIds;
    };

    protected string GetPlayerUid(int playerId) {
        return GetGame().GetBackendApi().GetPlayerIdentityId(playerId);
    };

    protected string GetPlayerName(int playerId) {
        return GetGame().GetPlayerManager().GetPlayerName(playerId);
    };

    protected int GetLocalPlayerId() {
        return GetGame().GetPlayerController().GetPlayerId();
    };

    protected string GetLocalPlayerUid() {
        return GetLocalPlayerUid_Direct();
    };

    protected string GetLocalPlayerName() {
        return GetPlayerName(GetLocalPlayerId()); 
    };

    protected string GetLocalPlayerUid_Id() {
        return GetPlayerUid(GetLocalPlayerId());
    };

    protected string GetLocalPlayerUid_Direct() {
        return GetGame().GetBackendApi().GetLocalIdentityId();
    };
};
