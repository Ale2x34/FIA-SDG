// FIA/Scripts/Game/SDG/SDG_FIAWhitelistComponent.c

[BaseContainerProps()]
class SDG_FIAWhitelistComponentClass : ScriptComponentClass
{
}

// Composant "placeholder" pour whitelist FIA.
// Pour l'instant il ne FAIT RIEN en jeu, il sert juste à compiler correctement.
// On ajoutera la logique plus tard une fois que l'éditeur refonctionne.
[ComponentEditorProps(
    category: "SDG/FIA",
    description: "Placeholder de whitelist FIA (actuellement sans effet)"
)]
class SDG_FIAWhitelistComponent : ScriptComponent
{
    // FactionKey FIA (stocké pour plus tard)
    [Attribute("FIA", UIWidgets.EditBox, "FactionKey de la FIA")]
    string m_sFIAFactionKey;

    // FactionKey de fallback (stocké pour plus tard)
    [Attribute("USA", UIWidgets.EditBox, "FactionKey fallback")]
    string m_sFallbackFactionKey;

    // 👉 Ta whitelist codée en dur (pour plus tard)
    ref array<string> m_aWhitelist = {
        "8c072912-5361-4e52-beb6-484f452738c4" // toi
        // ,"autre-uid-ici"
    };

    // Intervalle prévu pour des checks (non utilisé pour l'instant)
    [Attribute("5", UIWidgets.Slider, "Intervalle de vérification (sec, non utilisé pour l'instant)", "1 60 1")]
    float m_fCheckInterval;

    //------------------------------------------------------------------------------------------------
    override void EOnInit(IEntity owner)
    {
        super.EOnInit(owner);

        // On ne fait rien pour le moment, c'est volontaire.
        // Objectif: ne pas casser la compilation pour pouvoir ouvrir le World Editor.
        #ifdef ENABLE_DIAG
        Print("SDG_FIAWhitelistComponent initialisé (placeholder, aucune logique active).");
        #endif
    }

    // Pas d'autres fonctions : pas de FactionManager, pas de PlayerManager,
    // pas de Chat, donc pas d'erreurs de types ou de fonctions inconnues.
}
