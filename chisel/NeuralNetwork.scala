//> using scala "2.13.12"
//> using dep "org.chipsalliance::chisel:6.5.0"
//> using plugin "org.chipsalliance:::chisel-plugin:6.5.0"
//> using options "-unchecked", "-deprecation", "-language:reflectiveCalls", "-feature", "-Xcheckinit", "-Xfatal-warnings", "-Ywarn-dead-code", "-Ywarn-unused", "-Ymacro-annotations"
package lab2

import chisel3._
import _root_.circt.stage.ChiselStage

class NeuralNetwork extends Module {
  // AXI-Stream Connection
  val sAxis = Wire(new AxiStreamSlaveIf(16))
  IO(new AxiStreamExternalIf(16)).suggestName("s_axis").connect(sAxis)

  val mAxis = Wire(new AxiStreamMasterIf(16))
  IO(Flipped(new AxiStreamExternalIf(16))).suggestName("m_axis").connect(mAxis)

  
  val evenCounter = RegInit(0.U(8.W))
  val transferCount = RegInit(false.B)

  sAxis.tready := RegInit(true.B)
  mAxis.data.tvalid := RegInit(false.B)
  mAxis.data.tlast := RegInit(false.B)
  mAxis.data.tdata := RegInit(0.S(16.W))
  mAxis.data.tkeep := RegInit("b11".U)

  when(sAxis.data.tvalid) {
    when(sAxis.data.tdata(0) === false.B) {
      evenCounter := evenCounter + 1.U
    }
    when(sAxis.data.tlast) {
      transferCount := true.B
    }
  }


  val output_data = RegInit(-240.S(16.W))

  when(transferCount && mAxis.tready) {
    mAxis.data.tvalid := true.B
    mAxis.data.tlast := true.B
    mAxis.data.tdata := output_data
    evenCounter := 0.U
    transferCount := false.B
  }
}

object NeuralNetwork extends App {
  ChiselStage.emitSystemVerilogFile(
    new NeuralNetwork,
    firtoolOpts = Array("-disable-all-randomization", "-strip-debug-info")
  )
}
