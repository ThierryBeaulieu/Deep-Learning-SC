//> using scala "2.13.12"
//> using dep "org.chipsalliance::chisel:6.5.0"
//> using plugin "org.chipsalliance:::chisel-plugin:6.5.0"
//> using options "-unchecked", "-deprecation", "-language:reflectiveCalls", "-feature", "-Xcheckinit", "-Xfatal-warnings", "-Ywarn-dead-code", "-Ywarn-unused", "-Ymacro-annotations"
package lab2

import chisel3._
import _root_.circt.stage.ChiselStage
import scala.io.Source


object Util {
  def readCSV(filePath: String): Array[Array[Int]] = {
    val source = Source.fromFile(filePath)
    val data = source
      .getLines()
      .map { line =>
        line.split(",").map(_.trim.toInt)
      }
      .toArray
    source.close()
    data
  }
}

class MatrixModel extends Module {
  // AXI-Stream Connection
  val sAxis = Wire(new AxiStreamSlaveIf(8))
  IO(new AxiStreamExternalIf(8)).suggestName("s_axis").connect(sAxis)

  val mAxis = Wire(new AxiStreamMasterIf(8))
  IO(Flipped(new AxiStreamExternalIf(8))).suggestName("m_axis").connect(mAxis)
  
  val LabelW = 10
  val InputW = 401

  val rawData = Util.readCSV("weights.csv")
  val weights = VecInit.tabulate(LabelW, InputW){ (x, y) => rawData(x)(y).S(8.W) }
  
  val inputVector = RegInit(VecInit(Seq.fill(401)(0.U(8.W)))) 
  val inputCounter = RegInit(0.U(9.W))
  val inputReceived = RegInit(false.B)

  val outputReady = RegInit(false.B)
  val outputSent = RegInit(false.B)
  val outputCounter = RegInit(0.U)
  val result = RegInit(VecInit(Seq.fill(10)(0.S(8.W))))

  sAxis.tready := true.B
  mAxis.data.tvalid := false.B
  mAxis.data.tlast := false.B
  mAxis.data.tdata := 0.U
  mAxis.data.tkeep := "b1".U

  when(sAxis.data.tvalid) {
    inputVector(inputCounter) := sAxis.data.tdata
    inputCounter := inputCounter + 1.U
  }

  when(sAxis.data.tlast) {
    for (i <- 0 until LabelW) { 
      result(i) := 0.S
      for (j <- 0 until InputW) { 
        result(i) := result(i) + (weights(i)(j) * inputVector(j))
      }
    }
    inputCounter := 0.U
    outputReady := true.B
  }

  when(outputReady && mAxis.tready){
    mAxis.data.tvalid := true.B
    mAxis.data.tlast := false.B
    mAxis.data.tdata := result(outputCounter).asUInt
    when(outputCounter === 9.U) {
      mAxis.data.tlast := true.B
      outputReady := false.B
    }
    outputCounter := outputCounter + 1.U
  }
}

object MatrixModel extends App {
  ChiselStage.emitSystemVerilogFile(
    new MatrixModel,
    firtoolOpts = Array("-disable-all-randomization", "-strip-debug-info")
  )
}
