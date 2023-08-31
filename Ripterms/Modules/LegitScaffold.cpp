#include "Modules.h"

void Ripterms::Modules::LegitScaffold::onEvent(Ripterms::Event* event)
{
	if (event->type == Ripterms::Event::PRE_MOTION)
	{
		static bool sneaked = false;
		if (!enabled)
			return;
		static CTimer timer = std::chrono::milliseconds(delayMs);

		Minecraft theMinecraft = Minecraft::getTheMinecraft(event->env);
		EntityPlayerSP thePlayer = theMinecraft.getThePlayer();
		WorldClient theWorld = theMinecraft.getTheWorld();
		GameSettings gameSettings = theMinecraft.getGameSettings();
		KeyBinding keyBindSneak = gameSettings.getKeyBindSneak();

		bool checkSneak = true;
		if ((GetKeyState(0x53) & 0x8000) && thePlayer.isOnGround())
		{
			Ripterms::Maths::Vector3d playerPosition = thePlayer.getPosition();
			playerPosition.y -= 1.0f;
			BlockPos playerBlockPos = BlockPos::newObject(playerPosition, event->env);
			Block playerBlock = theWorld.getBlockState(playerBlockPos).getBlock();
			if (playerBlock.instanceOf(JavaClassV2("net/minecraft/block/BlockAir").getJClass(event->env)))
			{
				timer.setEvery(std::chrono::milliseconds(delayMs));
				sneaked = true;
				keyBindSneak.setPressed(true);
				checkSneak = false;
			}
		}
		if (checkSneak && sneaked && timer.isElapsed())
		{
			keyBindSneak.setPressed(false);
			sneaked = false;
		}
	}
}

void Ripterms::Modules::LegitScaffold::renderGUI()
{
	static bool display_options = false;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(20.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(250.0f, ImGui::GetStyle().FramePadding.y));
	ImGui::Checkbox("Legit Scaffold", &enabled);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		display_options = !display_options;
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 30.0f);
	if (ImGui::ArrowButton("lso", ImGuiDir_Down))
		display_options = !display_options;
	if (display_options)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::BeginGroup();
		ImGui::SliderInt("delay ms", &delayMs, 50, 300);
		ImGui::EndGroup();
	}
}