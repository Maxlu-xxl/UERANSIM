package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnOctetString;
import tr.havelsan.ueransim.asn.core.AsnSequence;
import tr.havelsan.ueransim.rrc.asn.integers.RRC_RejectWaitTime;

public class RRC_RRCReject_IEs extends AsnSequence {
    public RRC_RejectWaitTime waitTime; // optional
    public AsnOctetString lateNonCriticalExtension; // optional
    public RRC_nonCriticalExtension_25 nonCriticalExtension; // optional

    public static class RRC_nonCriticalExtension_25 extends AsnSequence {
    }
}
