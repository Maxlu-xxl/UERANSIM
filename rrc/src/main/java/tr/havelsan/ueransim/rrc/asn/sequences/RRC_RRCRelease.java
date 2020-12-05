package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnChoice;
import tr.havelsan.ueransim.asn.core.AsnSequence;
import tr.havelsan.ueransim.rrc.asn.integers.RRC_RRC_TransactionIdentifier;

public class RRC_RRCRelease extends AsnSequence {
    public RRC_RRC_TransactionIdentifier rrc_TransactionIdentifier; // mandatory
    public RRC_criticalExtensions_13 criticalExtensions; // mandatory

    public static class RRC_criticalExtensions_13 extends AsnChoice {
        public RRC_RRCRelease_IEs rrcRelease;
        public RRC_criticalExtensionsFuture_35 criticalExtensionsFuture;
    
        public static class RRC_criticalExtensionsFuture_35 extends AsnSequence {
        }
    }
}
