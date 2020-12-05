package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnChoice;
import tr.havelsan.ueransim.asn.core.AsnSequence;
import tr.havelsan.ueransim.rrc.asn.integers.RRC_RRC_TransactionIdentifier;

public class RRC_RRCReestablishmentComplete extends AsnSequence {
    public RRC_RRC_TransactionIdentifier rrc_TransactionIdentifier; // mandatory
    public RRC_criticalExtensions_22 criticalExtensions; // mandatory

    public static class RRC_criticalExtensions_22 extends AsnChoice {
        public RRC_RRCReestablishmentComplete_IEs rrcReestablishmentComplete;
        public RRC_criticalExtensionsFuture_30 criticalExtensionsFuture;
    
        public static class RRC_criticalExtensionsFuture_30 extends AsnSequence {
        }
    }
}
