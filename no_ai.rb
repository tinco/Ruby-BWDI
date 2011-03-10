require './bwdi'

module AI
  class NoAI
    attr_accessor :starcraft

    def start(game)
      @starcraft = game
      @frame = 0
      puts "match started, player_id: #{game.player_id}"
    end #start

    def on_frame
      @frame += 1
      if @frame % 24 == 0
        puts "had 24 frames"
      end
    end #on_frame

    def end
      puts "Match ended"
    end
  end
  RubyBWDI.run(NoAI.new)
end #module AI
