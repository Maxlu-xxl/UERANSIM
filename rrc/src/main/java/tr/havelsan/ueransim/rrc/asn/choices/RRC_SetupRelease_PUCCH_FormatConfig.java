package tr.havelsan.ueransim.rrc.asn.choices;

import tr.havelsan.ueransim.asn.core.AsnChoice;
import tr.havelsan.ueransim.asn.core.AsnNull;
import tr.havelsan.ueransim.rrc.asn.sequences.RRC_PUCCH_FormatConfig;

public class RRC_SetupRelease_PUCCH_FormatConfig extends AsnChoice {
    public AsnNull release;
    public RRC_PUCCH_FormatConfig setup;
}
