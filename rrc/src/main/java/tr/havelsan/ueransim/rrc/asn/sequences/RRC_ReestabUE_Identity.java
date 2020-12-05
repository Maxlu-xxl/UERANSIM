package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnSequence;
import tr.havelsan.ueransim.rrc.asn.bit_strings.RRC_ShortMAC_I;
import tr.havelsan.ueransim.rrc.asn.integers.RRC_PhysCellId;
import tr.havelsan.ueransim.rrc.asn.integers.RRC_RNTI_Value;

public class RRC_ReestabUE_Identity extends AsnSequence {
    public RRC_RNTI_Value c_RNTI; // mandatory
    public RRC_PhysCellId physCellId; // mandatory
    public RRC_ShortMAC_I shortMAC_I; // mandatory
}
