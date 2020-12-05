package tr.havelsan.ueransim.rrc.asn.sequences;

import tr.havelsan.ueransim.asn.core.AsnSequence;
import tr.havelsan.ueransim.rrc.asn.integers.RRC_FreqBandIndicatorNR;
import tr.havelsan.ueransim.rrc.asn.sequence_ofs.RRC_NR_NS_PmaxList;

public class RRC_NR_MultiBandInfo extends AsnSequence {
    public RRC_FreqBandIndicatorNR freqBandIndicatorNR; // optional
    public RRC_NR_NS_PmaxList nr_NS_PmaxList; // optional
}
