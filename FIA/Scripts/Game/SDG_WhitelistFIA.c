modded class SCR_PlayerFactionAffiliationComponent
{
	// Les UID sont ICI
	protected ref array<string> m_FiaWhitelistBackend = {
		"8c072912-5361-4e52-beb6-484f452738c4", // Ale2x_
		"45e7d5f0-243d-4d70-9173-6b6e01b326c1", // [FR]Norman
		"d848221f-f4f1-4ad9-a719-697cfe9caaab", // Galliax
		"4a5929a3-d3b9-4c6b-80e1-dbd9c55a78c5", // Baggzel
		"9786d92f-1d6b-46d4-a0bb-a2c7ff5e9989", // Dragon67
		"3a5d90103-fbee-4836-9df6-9fee53cb8b13", // -mousse
		"548ffdc3-ebec-4658-909e-82f8f44b6efb", // DXNomade
		"a5d90103-fbee-4836-9df6-9fee53cb8b13", // Aldriss
		"617ab078-8c1c-49f1-9fa0-fbc017b21324", // RaVag3uЯ
		"f25f74aa-40ca-4a09-82ff-efcaa4377b48", // Angev_2b
		"eaea4528-dca3-4626-8a36-8e6a259d9ed3", // Twafers
		"f75f7472-3da9-439d-8c5d-79d3ad0aa51e", // Valeb
		"c4e0c5f0-2b06-4f14-8e55-86695987f4f5", // vidock
		"6f0467ac-9392-47f7-8d67-0715689d7bed" // yannn057
	};

	override protected bool CanRequestFaction_S(Faction faction)
	{
		if (!super.CanRequestFaction_S(faction))
			return false;

		if (!faction)
			return false;

		if (faction.GetFactionKey() != "FIA")
			return true;

		int playerId = GetPlayerId();

		string backendId = string.Empty;
		BackendApi api = GetGame().GetBackendApi();
		if (api)
			backendId = api.GetPlayerIdentityId(playerId);

		Print(string.Format("WHITELIST DEBUG FIA: playerId=%1 backendId='%2'", playerId, backendId), LogLevel.WARNING);

		if (backendId.IsEmpty())
		{
			Print("WHITELIST(FIA): backendId vide -> refus FIA", LogLevel.WARNING);
			return false;
		}

		if (m_FiaWhitelistBackend.Find(backendId) == -1)
		{
			Print(string.Format("WHITELIST(FIA): backendId '%1' non whitelist -> refus FIA", backendId), LogLevel.WARNING);
			return false;
		}

		return true;
	}
}