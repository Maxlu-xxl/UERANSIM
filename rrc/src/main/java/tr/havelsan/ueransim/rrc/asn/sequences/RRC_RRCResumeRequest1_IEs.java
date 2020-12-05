package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnBitString;
import tr.havelsan.ueransim.asn.core.AsnSequence;
import tr.havelsan.ueransim.rrc.asn.bit_strings.RRC_I_RNTI_Value;
import tr.havelsan.ueransim.rrc.asn.enums.RRC_ResumeCause;

public class RRC_RRCResumeRequest1_IEs extends AsnSequence {
    public RRC_I_RNTI_Value resumeIdentity; // mandatory
    public AsnBitString resumeMAC_I; // mandatory, SIZE(16)
    public RRC_ResumeCause resumeCause; // mandatory
    public AsnBitString spare; // mandatory, SIZE(1)
}
