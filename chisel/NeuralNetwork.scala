//> using scala "2.13.12"
//> using dep "org.chipsalliance::chisel:6.5.0"
//> using plugin "org.chipsalliance:::chisel-plugin:6.5.0"
//> using options "-unchecked", "-deprecation", "-language:reflectiveCalls", "-feature", "-Xcheckinit", "-Xfatal-warnings", "-Ywarn-dead-code", "-Ywarn-unused", "-Ymacro-annotations"
package lab2

import chisel3._
import _root_.circt.stage.ChiselStage

class NeuralNetwork extends Module {
  // AXI-Stream Connection
  val sAxis = Wire(new AxiStreamSlaveIf(8))
  IO(new AxiStreamExternalIf(8)).suggestName("s_axis").connect(sAxis)

  val mAxis = Wire(new AxiStreamMasterIf(8))
  IO(Flipped(new AxiStreamExternalIf(8))).suggestName("m_axis").connect(mAxis)
  
  val input_data = VecInit(1.U, 2.U, 4.U, 8.U, 12.U, 15.U, 10.U, 22.U) // works with an
  val sending = RegInit(false.B)
  val receiveCounter = RegInit(0.U(3.W))
  val sendCounter = RegInit(0.U(3.W))
  val sum = RegInit(0.U(9.W))

  sAxis.tready := RegInit(true.B)
  mAxis.data.tvalid := RegInit(false.B)
  mAxis.data.tlast := RegInit(false.B)
  mAxis.data.tdata := RegInit(0.U)
  mAxis.data.tkeep := "b1".U

  when(sAxis.data.tvalid) {
    receiveCounter := receiveCounter + 1.U
    when(sAxis.data.tlast) {
      sending := true.B
      sAxis.tready := false.B
    }
  }
  when(sending && mAxis.tready) {
    mAxis.data.tvalid := true.B
    mAxis.data.tlast := false.B
    mAxis.data.tdata := input_data(sendCounter)
    sendCounter := sendCounter + 1.U
    
    when(sendCounter === receiveCounter - 1.U) {
      mAxis.data.tlast := true.B
      mAxis.data.tvalid := false.B
      sending := false.B
      receiveCounter := 0.U
      sendCounter := 0.U
    }
  }
}

object NeuralNetwork extends App {
  ChiselStage.emitSystemVerilogFile(
    new NeuralNetwork,
    firtoolOpts = Array("-disable-all-randomization", "-strip-debug-info")
  )
}
