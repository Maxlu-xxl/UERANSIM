package tr.havelsan.ueransim.rrc.asn.choices;

import tr.havelsan.ueransim.asn.core.AsnChoice;
import tr.havelsan.ueransim.asn.core.AsnNull;
import tr.havelsan.ueransim.rrc.asn.sequences.RRC_RateMatchPatternLTE_CRS;

public class RRC_SetupRelease_RateMatchPatternLTE_CRS extends AsnChoice {
    public AsnNull release;
    public RRC_RateMatchPatternLTE_CRS setup;
}
