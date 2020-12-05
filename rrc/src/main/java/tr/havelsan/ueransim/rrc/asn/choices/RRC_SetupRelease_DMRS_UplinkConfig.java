package tr.havelsan.ueransim.rrc.asn.choices;

import tr.havelsan.ueransim.asn.core.AsnChoice;
import tr.havelsan.ueransim.asn.core.AsnNull;
import tr.havelsan.ueransim.rrc.asn.sequences.RRC_DMRS_UplinkConfig;

public class RRC_SetupRelease_DMRS_UplinkConfig extends AsnChoice {
    public AsnNull release;
    public RRC_DMRS_UplinkConfig setup;
}
