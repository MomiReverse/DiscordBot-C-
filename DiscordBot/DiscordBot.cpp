#include <iostream>
#include <dpp/dpp.h>
#include <dpp/message.h>
#include <vector>
#include <Windows.h>

const std::string BOT_TOKEN = "TOKEN HERE"; // <-- Here BOT TOKEN 
const dpp::snowflake MY_GUILD_ID = 123021; // <-- Here GUILD ID


std::vector<std::string> links;


int main() {



    std::string link[16] = {"https://www.youtube.com/@TTTed_DBD\n", "https://www.youtube.com/channel/UCel9puPHf4yFwhSk5auoCiw\n", "https://www.youtube.com/channel/UCo3ZPKVPg3xMsrSMx3dQjLA\n" };

    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event) { // Create Command
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
        });   


    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "youtube") {
            dpp::user author = event.command.get_issuing_user();
            event.reply(author.get_mention() + "\n" + "https://www.youtube.com/@TTTed_DBD\n https://www.youtube.com/channel/UCel9puPHf4yFwhSk5auoCiw\n https://www.youtube.com/channel/UCo3ZPKVPg3xMsrSMx3dQjLA");
        }
        });


    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        if (event.msg.content == "TEDDY") {
            dpp::message msg(event.msg.channel_id, "123 123 123 123 Hosplay pidr");
            bot.message_create(msg);

            std::cout << " DEGUB: In: " << event.msg.channel_id << " reply to: " << event.msg.guild_id << "\n";
        }
    });








    bot.on_ready([&bot](const dpp::ready_t& event) { // Register command at bot
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(
                dpp::slashcommand("ping", "Ping pong!", bot.me.id)      
            );
            bot.global_command_create(
                dpp::slashcommand("youtube", "youtubelinks", bot.me.id)
            );
        }
        });



    bot.start(dpp::st_wait);

    return 0;
}