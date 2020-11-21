/*
 * Copyright (c) 2020 ALİ GÜNGÖR (aligng1620@gmail.com)
 * This software and all associated files are licensed under GPL-3.0.
 */

package tr.havelsan.ueransim.app.app.tester;

import tr.havelsan.ueransim.app.common.configs.ProcTestConfig;
import tr.havelsan.ueransim.app.common.enums.ERmState;
import tr.havelsan.ueransim.app.common.itms.IwUeTestCommand;
import tr.havelsan.ueransim.app.common.simctx.BaseSimContext;
import tr.havelsan.ueransim.app.common.simctx.UeSimContext;
import tr.havelsan.ueransim.app.common.testcmd.TestCmd_Deregistration;
import tr.havelsan.ueransim.itms.ItmsId;

class DeRegistrationTester extends UeTester {

    private UeTester otherTester;

    public DeRegistrationTester(UeSimContext ctx, ProcTestConfig config) {
        super(ctx, config);
    }

    @Override
    public void onStart() {
        otherTester = new InitialRegistrationTester(ctx, config) {
            @Override
            public void onComplete() {
                otherTester = null;

                ctx.itms.sendMessage(ItmsId.UE_TASK_APP,
                        new IwUeTestCommand(new TestCmd_Deregistration(false)));
            }
        };
        otherTester.onStart();
    }

    @Override
    public void onComplete() {
        if (otherTester != null) {
            otherTester.onComplete();
            return;
        }
    }

    @Override
    public void onConnected(BaseSimContext ctx, ConnType connType) {
        if (otherTester != null) {
            otherTester.onConnected(ctx, connType);
            return;
        }
    }

    @Override
    public void onSend(BaseSimContext ctx, Object message) {
        if (otherTester != null) {
            otherTester.onSend(ctx, message);
            return;
        }
    }

    @Override
    public void onReceive(BaseSimContext ctx, Object message) {
        if (otherTester != null) {
            otherTester.onReceive(ctx, message);
            return;
        }
    }

    @Override
    public void onSwitched(BaseSimContext ctx, Enum<?> state) {
        if (otherTester != null) {
            otherTester.onSwitched(ctx, state);
            return;
        }

        if (state == ERmState.RM_DEREGISTERED) {
            onComplete();
        }
    }
}