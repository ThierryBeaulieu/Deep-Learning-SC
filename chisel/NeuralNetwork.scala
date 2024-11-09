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


  val sending = RegInit(false.B)
  // val output_data = RegInit(Vec(Seq.fill(10)(0.S(16.W))))
  val output_data = VecInit(Seq(-1.S(16.W), -2.S(16.W), -3.S(16.W), -4.S(16.W), -5.S(16.W), -6.S(16.W), -7.S(16.W), -8.S(16.W), 1.S(16.W)))
  val transferCount = RegInit(0.U(4.W))

  sAxis.tready := RegInit(true.B)
  mAxis.data.tvalid := RegInit(false.B)
  mAxis.data.tlast := RegInit(false.B)
  mAxis.data.tdata := RegInit(0.S(16.W))
  mAxis.data.tkeep := RegInit("b11".U)

  when(sAxis.data.tvalid) {
    when(sAxis.data.tlast) {
      sending := true.B
    }
  }

  when(sending && mAxis.tready) {
    when (transferCount === output_data.length.U) {
      mAxis.data.tlast := true.B
      mAxis.data.tvalid := false.B
      transferCount := 0.U
    }.otherwise {
      mAxis.data.tlast := false.B
      mAxis.data.tvalid := true.B
      mAxis.data.tdata := output_data(transferCount)
      transferCount := transferCount + 1.U
    }
  }
}

object NeuralNetwork extends App {
  ChiselStage.emitSystemVerilogFile(
    new NeuralNetwork,
    firtoolOpts = Array("-disable-all-randomization", "-strip-debug-info")
  )
}
