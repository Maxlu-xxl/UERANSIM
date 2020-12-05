package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnOctetString;
import tr.havelsan.ueransim.asn.core.AsnSequence;
import tr.havelsan.ueransim.rrc.asn.sequence_ofs.RRC_InterFreqCarrierFreqList;

public class RRC_SIB4 extends AsnSequence {
    public RRC_InterFreqCarrierFreqList interFreqCarrierFreqList; // mandatory
    public AsnOctetString lateNonCriticalExtension; // optional
}
