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
  val sendCounter = RegInit(0.U(9.W))
  val receiveCounter = RegInit(0.U(9.W))
  val input_data = RegInit(VecInit(Seq.fill(401)(0.S(16.W))))

  sAxis.tready := RegInit(true.B) // ready to receive some data

  mAxis.data.tvalid := RegInit(false.B)
  mAxis.data.tlast := RegInit(false.B)
  mAxis.data.tdata := RegInit(0.S)
  mAxis.data.tkeep := RegInit("b1".U)

  when(sAxis.data.tvalid) { // the data is valid
    input_data(receiveCounter) := sAxis.data.tdata
    receiveCounter := receiveCounter + 1.U
    when(sAxis.data.tlast) { // the last data is here
      sending := true.B
      sAxis.tready := false.B // no longer ready to receive some data
    }
  }
  when(sending && mAxis.tready) { // when the receiver is ready
    mAxis.data.tvalid := true.B // it's true
    mAxis.data.tlast := false.B // not the last
    mAxis.data.tdata := input_data(sendCounter) //
  
    when(sendCounter === receiveCounter - 1.U) {
      mAxis.data.tlast := true.B
      mAxis.data.tvalid := false.B
      sending := false.B
      receiveCounter := 0.U
      sendCounter := 0.U
      sAxis.tready := true.B
    }.otherwise {
      sendCounter := sendCounter + 1.U
    }
  }
}

object NeuralNetwork extends App {
  ChiselStage.emitSystemVerilogFile(
    new NeuralNetwork,
    firtoolOpts = Array("-disable-all-randomization", "-strip-debug-info")
  )
}
